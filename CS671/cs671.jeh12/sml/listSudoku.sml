structure ListSudoku : SUDOKU = struct

type grid = int list

exception Parse
exception Unsolvable

fun parseString str = let
	val charList = explode str
	
	fun parsing [] l = l
	| parsing (h::t) l = if Char.isSpace h then parsing t l
					else if ord h > 0x2F && ord h < 0x3A then (ord h - 0x30):: parsing t l
					else 0:: parsing t l
					
	val parsed = parsing charList []
	
	fun checkParsed () = (List.length parsed) != 81
in
	if checkParsed () then raise Parse
	else parsed
end

fun get (g, i) = if checkIndex i then List.nth(g, i) else raise Unsolvable

fun set (g, i, v) = if checkIndex i && checkValue v then listSet(g, i, v) else raise Unsolvable

fun unsolved g = let
		fun checkGrid [] _ = NONE
		|	checkGrid (h::t) i = if h != 0 then checkGrid t (i+1)
								else SOME (i)
in
	checkGrid g 0
end

fun possibles (g,i) = if get(g,i) != 0 then [get(g,i)]
					else let
		val row = getRow g i
		val col = getCol g i
		val square = getSquare g i
		
		fun getPossibles n = if n > 9 then []
						else if contains row n then getPossibles (n+1)
						else if contains col n then getPossibles (n+1)
						else if contains square n then getPossibles(n+1)
						else n::getPossibles(n+1)
	in
		getPossibles 1
	end
	
fun valid g = if List.length g != 81 then false
		else if unsolved g != NONE then false
		else repeatTest g			
			
fun parseFile file =
    let open TextIO
        val s = openIn file
    in
      parseString (input s) before closeIn s
    end

fun sudoku g = if valid g then g
		else if unsolved g = NONE then raise Unsolvable
		else let
			val firstIndex = resolveSome(unsolved g)
				handle Trouble => raise Unsolvable
			val poss = possibles(g,firstIndex)
			
			fun solve [] = raise Unsolvable
				| solve (h::t) = sudoku(set (g,firstIndex,h))
					handle Unsolvable => solve t
		in
			solve poss
		end

	
local
    open TextIO
    fun ts 0 = "."
      | ts x = Int.toString x
    fun pr [] _ = ()
      | pr (x::l) n = (print (ts x); 
                       if n mod 9 = 0 then print "\n" else print " ";
                       pr l (n+1))
in
	fun print s = pr s 1
end

end


