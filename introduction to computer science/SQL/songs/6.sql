SELECT songs.name FROM SONGS JOIN artists ON artists.id = songs.artist_id WHERE artists.name == "Post Malone";