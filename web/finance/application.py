import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    rows = db.execute("SELECT * FROM port WHERE id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]
    totalcash = cash
    i = 0
    while i < len(rows):
        totalcash = totalcash + rows[i]["total"]
        i = i + 1
    return render_template("index.html", portlist = rows, cash = cash, totalcash = totalcash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("Missing symbol")
        elif not shares:
            return apology("Missing shares")
        elif int(shares) <= 0:
            return apology("Provide a positive number")
        elif not shares.isdigit():
            return apology("Invalid shares")
        search = lookup(symbol)
        if search == None:
            return apology("Invalid symbol")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        newcash = cash - search["price"] * int(shares)
        total = search["price"] * int(shares)
        if newcash < 0:
            return apology("Can't afford")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newcash, session["user_id"])

        rows = db.execute("SELECT * FROM port WHERE id = ? AND symbol = ?", session["user_id"], symbol)
        if len(rows) == 0:
            db.execute("INSERT INTO port (id, symbol, shares, name, price, total) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], symbol, int(shares), search["name"], search["price"], total)
        else:
            db.execute("UPDATE port SET shares = shares + ? WHERE id = ? AND symbol = ?", int(shares), session["user_id"], symbol)
            db.execute("UPDATE port SET total = shares * price WHERE id = ? AND symbol = ?", session["user_id"], symbol)

        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, int(shares), search["price"])
        return redirect("/")



@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT * FROM history WHERE id = ?", session["user_id"])
    return render_template("history.html",hislist = rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return("Missing symbol")
        quote = lookup(symbol.upper())
        if quote == None:
            return apology("Invalid Symbol")

        return render_template("quoted.html", name = quote["name"], price = quote["price"])



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        if not username:
            return apology("Must provide a username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not password:
            return apology("Must provide a password")
        elif not confirmation:
            return apology("Must confirm your password")
        elif password != confirmation:
            return apology("Password and Confirmation didn't match")
        hashpass = generate_password_hash(password)
        row = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(row) != 0:
            return apology("Username already exists")
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashpass)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocklist = db.execute("SELECT * FROM port WHERE id = ?", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html",stocklist = stocklist)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Missing symbol")
        elif not shares:
            return apology("Missing shares")
        elif not shares.isdigit():
            return apology("Invalid shares")
        elif int(shares) <= 0:
            return apology("Provide a positive number")
        search = lookup(symbol)
        if search == None:
            return apology("Invalid symbol")
        rows = db.execute("SELECT shares FROM port WHERE id = ? AND symbol = ?", session["user_id"], symbol)
        if len(rows) == 0:
            return apology("You don't have these stocks to sell")
        stocks = rows[0]["shares"]
        shares = int(shares)
        if stocks < shares:
            return apology("More shares that you have")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        newcash = cash + search["price"] * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newcash, session["user_id"])
        if stocks - shares > 0:
            db.execute("UPDATE port SET shares = shares - ? WHERE id = ? AND symbol = ?", shares, session["user_id"], symbol)
        else:
            db.execute("DELETE FROM port WHERE id = ? AND symbol = ?",session["user_id"], symbol)

        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, -(shares), search["price"])

        return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "GET":
        return render_template("add.html")
    else:
        money = request.form.get("money")
        if not money:
            return apology("Must type some amount of money")
        elif not money.isdigit():
            return apology("Must provide a number")
        money = int(money)
        if money == 0 or money < 0:
            return apology("Must provide a number bigger than 0")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", money, session["user_id"])
        return redirect("/")


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "GET":
        return render_template("change.html")
    else:
        password = request.form.get("password")
        if not password:
            return apology("Must provide your current password")
        newpass = request.form.get("newpass")
        confirmation = request.form.get("confirmation")
        if not newpass:
            return apology("Must provide a new password")
        elif not confirmation:
            return apology("Must confirm your new password")
        elif newpass != confirmation:
            return apology("New password and Confirmation didn't match")
        row = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        if not check_password_hash(row[0]["hash"], password):
            return apology("Wrong password")
        newpass = generate_password_hash(newpass)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", newpass, session["user_id"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
