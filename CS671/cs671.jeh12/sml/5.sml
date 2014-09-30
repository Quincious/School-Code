fun last [] = raise Empty
| last (h::[]) = h
| last (_::t) = last t;

fun natList 0 = []
| natList x = let
	fun tailRec 0 y = y
	| tailRec x y = tailRec(x-1)(x::y)
	in tailRec x []	end;
	
fun sum [] = 0
| sum (x::y) = x + sum y;

fun prod [] = 1
| prod (x::y) = x * prod y;

fun sum2 [] = 0
| sum2 (x::y) = sum x + sum2 y;

fun isLetter x = ((ord x <= 0x5A andalso ord x >= 0x41)
	orelse (ord x <= 0x7A andalso ord x >= 0x61));
	
fun toLower x = 
	if isLetter x then
		if(ord x <= 0x5A andalso ord x >= 0x41)
		then chr(ord x + 0x20)
		else x
	else x;
	
(*Return list minus last element*)	
fun removeLast [] = raise Empty
  | removeLast (x::[]) = []
  | removeLast (x::y::[]) = x::[]
  | removeLast (x::z) = x::(removeLast z)	
	
fun palindrome s = let
	(*Turn String into List*)
    val sl = explode s
	
	(*Compress to list without spaces*)
    fun compress [] = []
      | compress (c::[]) = if isLetter c then (c::[]) else []
      | compress (c::sl) = if isLetter c then ((toLower c)::(compress sl)) else (compress sl)
    val comp = compress sl
    
	(*create list containing head and tail(for comparing)*)
    fun hdtl (x::[]) = (x::[])
      | hdtl l = ((hd l)::(last l)::[])
	  
	(*Go through list, testing first and last, removing them after testing*)  
    fun test [] = true
      | test (x::[]) = true
      | test (x::y::[]) = (x=y)
      | test l = test (hdtl l) andalso test (removeLast (tl l))	  
in test comp end;

fun hanoi (1,A,B,C) = (A,C)::[]
  | hanoi (n,A,B,C) = hanoi((n-1),A,C,B)@(A,C)::hanoi((n-1),B,A,C);
  
  


(*Helper function for square root of int*)	
fun introot n=Real.floor (Math.sqrt (Real.fromInt n))

(*Helper function that Builds a list of prime numbers less than a given input*)
fun getPrimes n = let
    val num = n
	
	(*Test if number is prime by checking if divisible against list of primes*)
    fun testPrime x (p::[]) = not(x mod p = 0)
      | testPrime x (p::t) = if not(x mod p = 0) then testPrime x t 
						else false
	
	(*Build a list of all prime numbers less than input*)	
    fun sieve x l n= if x > n then l 
					else if (testPrime x l) then sieve (x+2) (x::l) n 
					else sieve (x+2) l n
in sieve 9 ([7,5,3,2]) n end

fun myLen [] = 0
| myLen (h::[]) = 1
| myLen l = let
	fun myLenCont [] count = count
	| myLenCont (h::t) count = myLenCont t (count+1)
in myLenCont l 0 end;

fun filt l = let
    val h = hd (!l)
    val t = tl (!l)
    val f=fn y => h=y
    val g=(not o f)
    val num = myLen (List.filter f (h::t))
in (l:=List.filter g t;num) end  

fun factor n = let
    val primes = getPrimes(introot n)
    val factors=[]
    (*actual factoring*)
    fun decompose n [] [] = (n::[])
	| decompose n [] l = (n::l)
	| decompose (n:int) (h::t) (l:int list) = if op*(h,h) > n then
													if n>1 then (n::l)
													else l
												else if (n mod h)=0 then
													decompose (op div(n,h)) (h::t) (h::l)
												else decompose n t l
      
    (*formatting of answer. combining all repeats to a tuple aka [2,2,2,2,3,3] => [(2,4),(3,2)]*)
    fun collect (x:int list ref) (l:(int*int) list) =
        if (!x)=[] then l 
		else let
			val q = hd(!x)
			val flt = filt x
    in collect x ((q,flt)::l) end

    val facts = decompose n (rev primes) factors
    val f_list = ref facts
in collect f_list ([]:(int*int) list) end

(*Helper Function to raise a number to another number*)  
fun intpow n 0 = 1
| intpow n e = let
	fun calcPow 0 num retVal = retVal
	  | calcPow exp num retVal = calcPow (exp-1) num (retVal*num)
in calcPow (e-1) n n end

(*Helper function to expand tuple and apply to function*)
fun expand f (x,y) = f x y

(*Helper function that takes a tuple of ints and raises the 1st value to the 2nd value *)
fun powint (n,e) = expand intpow (n,e)

fun multiply l =
    let fun mult [] r = r
          | mult (h::t) r = (mult t r) * powint(h)
    in mult l 1 end

fun printFact n=let
    val factors=rev (factor n);(*if ans is prime return "x is prime"*)
    fun strpow (x:(int*int)) = if #2(x) = 1 then Int.toString(#1x) else
                               concat (Int.toString(#1x)::"^"::Int.toString(#2x)::[])
	
	fun contains [] _ = false
		| contains _ [] = true
		| contains (str::[]) (sub::[]) = (str = sub)
		| contains (strH::strT) (subH::subT) = if(strH = subH)
											then contains strT subT
											else contains strT (subH::subT)
	
	fun acc (h::[]) [] = if contains (explode (strpow h)) [#"^"] then concat ((strpow h)::[])
							else concat ((strpow h)::" is prime\n"::[])
		| acc (h::[]) l = concat ((strpow h)::l)
		| acc (h::t) l = acc t (" * "::(strpow h)::l)
	
	fun printThis n factStr = if contains (explode factStr) [#"p",#"r",#"i",#"m",#"e",#"\n"] then print factStr
							else print (concat ((Int.toString n)::" = "::factStr::"\n"::[]))
	  
    val fact_str=acc factors []
in printThis n fact_str end

fun isPerm ([],[]) = true
  | isPerm ((h::[]),[]) = false
  | isPerm ([],(h::[])) = false
  | isPerm ((h::t),l) = let
      fun rot x (h::[]) [] = if h = x then [] else (h::[])
        | rot x (h::[]) l = if h = x then l else []
        | rot x [] l = []
        | rot x (h::t) l = if h = x then (t@l)
                            else rot x t (h::l)
  in isPerm (t,(rot h l [])) end