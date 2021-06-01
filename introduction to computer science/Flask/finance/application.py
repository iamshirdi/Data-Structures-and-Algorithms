import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
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
    """Show portfolio of stocks"""
    uid=session["user_id"]


    stocks= db.execute("SELECT symbol,shares FROM transcations where user=?",uid)
    for row in stocks:
        dic=lookup(row['symbol'])
        row['name']=dic['name']
        row['price']=dic['price']
        row['total']=dic['price']*row['shares']
    c = db.execute("SELECT cash FROM users where id=?",uid)
    cash=c[0]['cash']
    return render_template("index.html",stocks=stocks,cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        l = lookup(request.form.get("symbol"))
        if not l:
            return apology("invalid symbol")
        name = l['symbol']
        try:
            ns = int(request.form.get("shares"))
            if not (ns>0):
                return apology("positive number enter")
        except:
            return apology("invalid number")

        cc = db.execute("SELECT cash from  users where id=?",session["user_id"] )
        current_cash=cc[0]['cash']
        print(current_cash)
        spent_cash = l['price']*ns
        if (current_cash<spent_cash):
            return apology("invalid cash")
        time=datetime.datetime.now()
        csh = current_cash-spent_cash
        uid=session["user_id"]
        db.execute("UPDATE users SET cash= ? WHERE id = ?",csh,uid)
        check =  db.execute("SELECT * from transcations where symbol=?",name )
        if len(check)>0:
            db.execute("UPDATE transcations SET shares= ?,price=?,time=? WHERE user = ? AND symbol=?",ns+check[0]['shares'],l['price'],time.strftime('%Y-%m-%d'),uid,name)
        else:
            db.execute("INSERT INTO transcations (user,symbol,price,shares,time) VALUES (?,?,?,?,?)",session['user_id'],name,l['price'],ns,time.strftime('%Y-%m-%d'))
        db.execute("INSERT INTO purchase (user,name,symbol,price,shares,time) VALUES (?,?,?,?,?,?)",session['user_id'],l['name'],name,l['price'],ns,time.strftime('%Y-%m-%d'))

        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    uid=session["user_id"]

    stocks1= db.execute("SELECT user,symbol,shares,name,price,time FROM purchase where user=?",uid)
    for row in stocks1:
        row['total']=row['price']*row['shares']

    stocks2= db.execute("SELECT user,symbol,shares,name,price,time FROM purchase where user=?",uid)
    for row in stocks2:
        row['total']=row['price']*row['shares']
    stocks=stocks1+stocks2


    c = db.execute("SELECT cash FROM users where id=?",uid)
    cash=c[0]['cash']
    return render_template("history.html",stocks=stocks,cash=cash)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["user"] = rows[0]["username"]

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
    """Get stock quote."""
    if request.method == "POST":
        g = request.form.get("symbol")
        q = lookup(g)
        if not q:
            return apology("invalid code")

        return render_template("quoted.html",q=q)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        u = request.form.get("username")
        arg =request.form.get("password")
        p = generate_password_hash(arg)
        rp= request.form.get("confirmation")
        rp2 =check_password_hash(p, rp)
        db_check = db.execute("SELECT * from users WHERE username = ?",u)
        print(u,p,rp2,arg,rp)
        if not (u and p and rp2 and rp) :
             return apology("please enter valid username or password")
        if len(db_check)>0:
             return apology("username already exists")
        else:
            db.execute("INSERT into users (username,hash) VALUES(?,?)",u,p)
            return render_template("login.html")
    if request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    uid=session["user_id"]
    if request.method == "POST":

        l=request.form.get("symbol")
        ls = db.execute("select * from transcations where symbol = ? AND user = ?",l,uid)
        if not (l and len(ls)>0):
            return apology("invalid symbol or no stock")
        ns = int(request.form.get("shares"))
        print(ls)
        s = ls[0]['shares']
        if not (s>0 and s>ns ):
            return apology("not enough shares")
        cc = db.execute("SELECT cash from  users where id=?",session["user_id"] )
        current_cash=float(cc[0]['cash'])
        print(current_cash)
        c = lookup(l)
        current=float(c['price'])
        print("current is ",current,ns)
        spent_cash = current*float(ns)
        time=datetime.datetime.now()
        print(current_cash,spent_cash)
        csh = current_cash+spent_cash
        uid=session["user_id"]
        db.execute("UPDATE users SET cash= ? WHERE id = ?",csh,uid)
        rem=int(ls[0]['shares'])-ns
        price=int(ls[0]['shares'])*ls[0]['price'] - ns*current
        if rem == 0:
            db.execute("DELETE FROM transcations WHERE symbol=?",l);
        else:
            db.execute("UPDATE transcations SET price= ?,shares=?,time=?  WHERE symbol = ? AND user = ?",price,rem,time,l,uid)

        print("valid is ",session,l,ls,ns,time)
        db.execute("INSERT INTO purchase (symbol,name,price,shares,time) VALUES (?,?,?,?,?)",l,'sold',float(ls[0]['price']),ns,time.strftime('%Y-%m-%d'))

        return redirect("/")
    query = db.execute("select * from transcations where user = ?",uid)
    return render_template("sell.html",rows=query)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
