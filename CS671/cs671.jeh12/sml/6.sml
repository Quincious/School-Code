(*Jonathan Hart*)

fun quickSort filt l = let
    val f = List.filter
    fun quick [] = []
      | quick (h::[]) = [h]
      | quick (h::t) = let
          val pred = fn y => filt (y,h)
      in quick (f pred t)@h::(quick (List.filter (not o pred) t)) end
in quick l end

val _ = use "helper.sml";
val _ = use "sudoku-sig.sml";
val _ = use "listSudoku.sml";

local
	fun loop (x::y::zs, xs, ys) = loop (zs, x::xs, y::ys)
	| loop (x::[], xs, ys) = (x::xs, ys)
	| loop ([], xs, ys) = (xs, ys)
in
	fun split ns = loop(List.rev ns, [], [])
end

fun merge filt (xs,ys) = let
	fun loop (out, left as x::xs, right as y::ys) = 
			if filt (x,y) then loop (x::out, xs, right)
			else loop (y::out, left,ys)
	| loop (out, x::xs, []) = loop (x::out,xs,[])
	| loop (out, [], y::ys) = loop (y::out,[],ys)
	| loop (out, [], []) = List.rev out
in
	loop([],xs,ys)
end

fun mergeSort filt ls = let
	val mrg = merge filt
	fun sort [] = []
	| sort (h::[]) = [h]
	| sort l = let
		val (left, right) = split l
		in
			mrg (sort left, sort right)
		end
in
	sort ls
end

exception CannotChange

fun change _ 0 = []
	| change [] _ = raise CannotChange
	| change (coin::coins) amt =
		if coin > amt then
			change coins amt
		else
			(coin :: change coins (amt-coin))
				handle CannotChange => change coins amt

	   
fun changeBest coins amt = let

	val f1 = fn n => n <= amt
	
	val validCoins = List.filter f1 coins
	
	val allCoinCombos = subsets validCoins amt
	
	(*val f2 = fn l => (listSum l) = amt
									
	val filteredCoins = List.filter f2 allCoinCombos*)
	
	fun getShortest [] = raise CannotChange
		| getShortest (h::[]) = h
		| getShortest (h::t) = 
			let
				val l = getShortest t
			in
				if (List.length h) < (List.length l) then h else l
			end
		

in
	getShortest allCoinCombos
end
	
	
		
			

