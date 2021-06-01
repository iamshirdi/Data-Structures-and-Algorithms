SELECT m.title FROM movies m
JOIN ratings on m.id = ratings.movie_id
JOIN stars s on s.movie_id = m.id
JOIN people p on p.id = s.person_id
WHERE p.name == "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;