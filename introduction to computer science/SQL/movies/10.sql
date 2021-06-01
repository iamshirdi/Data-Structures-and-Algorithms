SELECT p.name FROM people p
JOIN directors ON directors.person_id = p.id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating>=9.0;
