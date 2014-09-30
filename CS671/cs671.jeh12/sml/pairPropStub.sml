structure PairProp : PROP where type state = BoolPairState.state = struct

type state = BoolPairState.state

datatype prop = Ident of string
              | T | F
              | And of prop * prop
              | Or of prop * prop
              | Implies of prop * prop
              | Not of prop

datatype value = True | False | Unknown

exception Parse of string

fun eval _ = raise Fail "not implemented"
fun tokenize _ = raise Fail "not implemented"
fun identifiers _ = raise Fail "not implemented"
fun satisfy _ = raise Fail "not implemented"
fun isValid _ = raise Fail "not implemented"

(* parsing code *)
fun iParse s = case oParse s of
                   (e1, "->" :: l) => let val (e2, r) = iParse l in
                                          (Implies(e1,e2), r)
                                      end
                 | r => r
and oParse s = case aParse s of
                   (e1, "|" :: l) => let val (e2, r) = oParse l in
                                         (Or(e1,e2), r)
                                     end
                 | r => r
and aParse s = case nParse s of
                   (e1, "&" :: l) => let val (e2, r) = aParse l in
                                         (And(e1,e2), r)
                                     end
                 | r => r
and nParse ("~" :: l) = let val (e, r) = nParse l in (Not e, r) end
  | nParse s = vParse s
and vParse ("(" :: l) = (case iParse l of
                             (e, ")" :: r) => (e, r)
                           | _ => raise Parse ("Missing closing parenthesis"))
  | vParse ("True" :: r) = (T, r)
  | vParse ("False" :: r) = (F, r)
  | vParse (w :: r) = if Char.isAlpha (hd (explode w)) then (Ident w,r)
                      else raise Parse ("Unexpected token: "^w)
  | vParse [] = raise Parse ("Missing identifier")

fun parse s = case iParse (tokenize s) of
                  (e, []) => e
                | (_, t :: _) => raise Parse ("Unexpected token: "^t)

end
