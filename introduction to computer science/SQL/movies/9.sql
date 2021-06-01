SELECT p.name from people p
JOIN stars ON p.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004 
ORDER BY p.birth
;