
(*helper operations
allow me to use Java and C++ techniques*)
infix += fun a += b = a:=(!a)+b
infix != fun a != b = a<>b
infix || fun a || b = a orelse b 
infix && fun a && b = a andalso b 
infix % fun a % b = a mod b

exception Trouble

(*helper functions*)
fun listInit (1,v) = [v]
	| listInit (i,v) = v::listInit((i-1), v)
	
fun listSet (h::t, 0, x) = x::t
	| listSet (h::t, i, x) = h:: listSet(t,(i-1),x);
	
fun contains l x = let
    val check = fn n => n=x
in List.exists check l end

fun resolveSome NONE = raise Trouble (*SHould not reach here*)
	| resolveSome x = valOf x
	
fun checkIndex i = (i>=0 && i<=80)

fun checkValue i = (i>=0 && i<=9)

fun listSum [] = 0 
	| listSum (h::t) = h + listSum t

fun seq m n = let
    val stop = (m-1)
    fun build n l = if n=stop then l else build (n-1) (n::l)
in build n [] end

fun getRow g i = let
	val rowNum = i div 9
	val firstIndex = rowNum * 9
	val lastIndex = firstIndex + 8
	
	fun row n = if (n = lastIndex) then [List.nth (g,n)]
			else List.nth(g,n):: row (n+1)
in
	row firstIndex
end

fun getAllRows g = let
	fun rows n = if n > 80 then []
			else (getRow g n)::rows(n+9)
in
	rows 0
end

fun getCol g i = let
	fun getColNum n = if n < 9 then n
					else getColNum (n-9)
	
	val colNum = getColNum i
	
	fun col n = if (n > 8) then []
			else List.nth(g, (colNum + (n*9))):: col (n+1)
in
	col 0
end

fun getAllCols g = let
	fun cols n = if n > 8 then []
			else (getCol g n)::cols (n+1)
in
	cols 0
end

fun getSquare g i = let
	fun getColNum n = if n < 9 then n
					else getColNum (n-9)
	
	val colNum = getColNum i
	val rowNum = i div 9
	
	fun getSections n = if n < 3 then [0,1,2]
					else if n < 6 then [3,4,5]
					else [6,7,8]
	
	val rowNums = getSections rowNum
	val colNums = getSections colNum
	
	fun square [] _ = []
		| square (rh::rt) (ch::[]) = List.nth(g,(ch + (rh*9))):: square rt colNums
		| square (rl as rh::_) (ch::ct) = List.nth(g,(ch + (rh*9))):: square rl ct
		
in
	square rowNums colNums
end

fun getAllSquares g = let
	fun squares [] = []
		| squares (h::t) = (getSquare g h)::squares t
in
	squares [0,3,6,27,30,33,54,57,60]
end

fun repeatTest g = let
	val row = getAllRows g 
	val col = getAllCols g
	val square = getAllSquares g
	
	fun checkAllRows _ [] = false
	| checkAllRows n (h::t) = if contains h n then checkAllRows n t
								else true
					
	fun checkAllCols _ [] = false
	| checkAllCols n (h::t) = if contains h n then checkAllCols n t
								else true
					
	fun checkAllSquares _ [] = false
	| checkAllSquares n (h::t) = if contains h n then checkAllSquares n t
								else true
	
	fun checkSections n = if n > 9 then true
					else if checkAllRows n row then false
					else if checkAllCols n col then false
					else if checkAllSquares n square then false
					else checkSections (n+1)
					
in 
	checkSections 1
end
						
	
fun popList x = 
	(let val y = (!x) 
	in x:=(tl y);hd(y)end)

fun clone lis = let
    val temp = lis
in temp end	

fun pc h = fn z => h::z

val sl_to_list = fn y=>ArraySlice.foldr (op ::) [] y

fun rot arr i = let
    val mid = Array.sub (arr,i)
    val left = ArraySlice.slice (arr,0,SOME(i))
    val right = ArraySlice.slice (arr,(i+1),NONE)
in mid::(sl_to_list right)@(sl_to_list left) end
	
fun strip str =let
    val chars = explode str
    val f = (not o Char.isSpace)
in List.filter f chars end

fun second (a,b) = b
fun first (a,b) = a

(*fun subsets xs amt = 
let
    fun subsets2 []      base = if listSum base = amt then [base] else []
      | subsets2 (x::xr) base = subsets2 xr base @ subsets2 xr (x::base)
in
    subsets2 xs []
end*)

fun subsets xs amt = let
    fun subsets2 []      base res = if listSum base = amt then base :: res else res
      | subsets2 (x::xr) base res = 
	subsets2 xr base (subsets2 xr (x::base) res)
in
    subsets2 xs [] []
end



