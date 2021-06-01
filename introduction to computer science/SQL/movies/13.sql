SELECT people.name from people
JOIN stars on people.id = stars.person_id
JOIN movies on movies.id = stars.movie_id
WHERE movies.id IN
(SELECT m.id FROM movies m
JOIN stars s on s.movie_id = m.id
JOIN people p on p.id = s.person_id
WHERE p.name == "Kevin Bacon" AND p.birth = 1958) 
AND people.name != "Kevin Bacon"
;

