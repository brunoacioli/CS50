SELECT AVG(rating) AS Average FROM ratings JOIN movies ON movies.id = ratings.movie_id WHERE movies.year = 2012