-- Keep a log of any SQL queries you execute as you solve the mystery.

-- check what data is and log of interview
-- theft took place at 10.15am
SELECT * FROM crime_scene_reports
WHERE street = "Chamberlin Street"
AND month = 7
AND day = 28
AND year = 2020
;

-- check for 3 interviews description on following day

SELECT * FROM interviews
WHERE transcript LIKE "%courthouse%"
AND month = 7
AND day = 28
AND year = 2020
;

-- security footage parking lot :time 10mins of theft so <10.25 around within 10 mins of theft
SELECT * FROM courthouse_security_logs
WHERE hour = 10
AND month = 7
AND minute >15
AND day = 28
AND year = 2020
AND activity = "exit";


-- ATM fifer street withdrawing money : Eugene Recognises time monring before 10.15 :: wihtdraw
SELECT * from atm_transactions
WHERE atm_location = "Fifer Street"
AND month = 7
AND day = 28
AND year = 2020
;

-- check accounts then persons since we have numbers
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN
(SELECT account_number from atm_transactions
WHERE atm_location = "Fifer Street"
AND month = 7
AND day = 28
AND year = 2020
AND transaction_type ="withdraw"))
;


-- earliset flight out of fiftyville on 29/7/2020 only 30 available flight: other end to purchase ticket
SELECT * FROM flights tf
JOIN airports ON tf.origin_airport_id = airports.id
WHERE city = "Fiftyville"
AND month =7
AND day =29
AND year =2020
ORDER BY hour
;

-- check passengers matching with passports
SELECT * FROM people
WHERE passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id IN
(
SELECT tf.id FROM flights tf
JOIN airports ON tf.origin_airport_id = airports.id
WHERE city = "Fiftyville"
AND month =7
AND day =29
AND year =2020
ORDER BY hour
LIMIT 1
)


)
;



-- Match license with parking lot licesnes


-- Check Phone records for matching name for accomplice need to pinpoint using flight tickets possibly :less than min


SELECT * FROM phone_calls
WHERE
month = 7
AND day = 28
AND year = 2020
AND( caller = "(389) 555-5198" OR
caller = "(367) 555-5533")
;

-- check reciever person
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
-- 236 | (367) 555-5533 | (344) 555-9601 | 2020 | 7 | 28 | 120
-- 245 | (367) 555-5533 | (022) 555-4052 | 2020 | 7 | 28 | 241
-- 285 | (367) 555-5533 | (704) 555-5790 | 2020 | 7 | 28 | 75
SELECT * from people
WHERE phone_number = "(375) 555-8161"
;

-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0


-- check destination city escaped to in flights

SELECT tf.id FROM flights tf
JOIN airports ON tf.origin_airport_id = airports.id
WHERE city = "Fiftyville"
AND month =7
AND day =29
AND year =2020
ORDER BY hour
LIMIT 2
;

SELECT * from people where name = "Ernest";

-- flight id is 36
SELECT passengers.passport_number,passengers.flight_id FROM passengers
JOIN people p ON p.passport_number = passengers.passport_number
WHERE (flight_id = 36 OR flight_id = 43) AND p.passport_number = 1988161715;

select * from flights where id =36;
-- destination airport is 4
select * from airports;
--London


