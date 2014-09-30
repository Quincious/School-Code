
val _ = use "helper.sml";

structure ListSudoku : SUDOKU = struct

type grid = int list

exception Parse
exception Unsolvable
val Get = List.nth
val Set = listSet
val seq9 = seq 1 9
val slice = ArraySlice.slice
val check = fn i=> (i<0 || i>80)
fun init () = listInit (81,0)
fun get (l,i) = if check i then Get (l,i) else raise Unsolvable
fun set (l,i,x) = if check i then Set(l,i,x) else raise Unsolvable


fun parseString str = let
    val chrs = strip str
    val g = init ()
    fun set i = let 
		val c = ord (Get (chrs,i)) 
		in
        if 0x31<=c && c<=0x39 then Set (g,i,(c-0x30))
        else Set (g,i,0) 
		end
		
    fun loop i = if i=0 then () 
				else (set (i-1);loop (i-1))
				
in 
	if List.length chrs != 81 then raise Parse 
	else (loop 81;g) 
end

(* if for some element i in grid #1(i) = 0 then SOME(i)
else NONE*)
fun unsolved board = let
    fun for ~1 lis = NONE
    | for i lis = if (get(lis,i) = 0) then SOME(i) 
	else for (i-1) lis
in for 80 board end

fun possibles (lis,i) =
    (check i;if (Get (lis,i))>0 then (Get (lis,i))::[]
                                 else (Get (lis,i)))
fun parseFile file =
    let open TextIO
        val s = openIn file
    in
      parseString (input s) before closeIn s
    end

fun row i = seq (i*9) (((i+1)*9)-1)

fun column j = let
    val inc = fn n => n+9
    val test = fn n => n>=81
    fun loop n f g x = if f n then rev x
                         else loop (g n) f g (n::x)
in loop j test inc [] end

fun block k = let
    val j = (if (k % 3) = 0 then 0 else if (k % 3) = 1 then 3
            else 6)
    val i = (if j = 0 then k else if j = 3 then k-1 else k-2)

in (9*(i)+j)::(9*(i)+j+1)::(9*(i)+j+2)::(9*(i+1)+j)::(9*(i+1)+j+1)::(9*(i+1)+j+2)::(9*(i+2)+j)::(9*(i+2)+j+1)::(9*(i+2)+j+2)::[] end

fun board_loop b f = let
    fun iter 0 0 = []
      | iter 0 j = iter 8 (j-1)
      | iter i j = case j of
                       1 => (f b (block i);iter (i-1) j)
                         | 2 => (f b (column i);iter (i-1) j)
                             | 3 => (f b (row i);iter (i-1) j)
in iter 8 3 end
(*test if board solved correctly*)
exception Unsolved
fun check b = let
    fun chk b rcb = let
        fun complete [] l =
            if (quickSort (op <) l) = (seq 1 9)
                        then () else raise Unsolved
		| complete (x::xs) l = complete xs ((Get(b,x))::l)
    in complete rcb [] end
in board_loop b chk end
fun singletons a [] = ()
  | singletons a (l::ls) = (if List.length (Get(a,l)) = 1
                            then ignore(Set(a,l,(hd(Get(a,l)))))
                            else ();singletons a ls)

fun forced a l = let
    val collect = listInit (9,[])
    
    val q = ref 0
    fun fori [] = ()
      | fori (x::xs) = let
          val ls = Get(a,x)
          fun forj [] = ()
            | forj (y::ys) =
              (Set (collect,(!q),(y::(Get(collect,(!q)))));forj ys)
      in (forj ls;q+=1;fori xs) end
    fun forc ~1 = ()
      | forc i = let
          val c = Get (collect,i)
      in (if List.length c = 1 then Set (a,(hd c),(i,[])) else [];forc (i-1))end
in (fori l;forc 8) end
fun getRCB i = let
    val triple = listInit(3,9)
    val rows = List.map row (seq 0 8)
    val cols = List.map column (seq 0 8)
    val blks = List.map block (seq 0 8)
    fun getsec x j ~1 = raise Subscript
    | getsec x j i = if contains (Get (x,i)) j then i
                     else getsec x j (i-1)
in [(getsec rows i 8),(getsec cols i 8),(getsec blks i 8)] end
(*update possible values for all undecided cells in the same
*row,collumn and block as i*)
fun update a i = let
    val x = Get(a,i)
    val RCB = ref (getRCB x)
    val row = row (popList RCB)
    val col = column (popList RCB)
    val blk = block (popList RCB)
    val check = fn k => k = x
    val update = fn n=>Set (a,n,(Get (a,n)))
    fun for j (l::ls) = if j = ~1 then () else (update l;for (j-1) ls)
in (for 8 row;for 8 col;for 8 blk) end
fun main board =
    
	
while (unsolved board != NONE) do
      let val old = clone board
          val _ = board_loop board singletons
      in if board = old then (board_loop board forced;
                              if board = old then
                              (*guess*)() else ())
         else () end
(*true iff grid filled and consistant*)
fun valid board = (check board;true)
                  handle Unsolved => false
(*Solves given grid*)
fun sudoku board = main board
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