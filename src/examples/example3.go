// Program 3: Prace s retezci a vestavenymi funkcemi
package main

func main() {
c := 4
b := 3+20*c/5
a := (b+20)*4

print("Vysledek_prvni_casti\n")
print(a, "\n")
a = uh_oh(1,2,3,4)
print("Vysledek_druhe_casti\n")
print(a, "\n")


}


func uh_oh(a int, b int, c int, d int)(int){

  return a + b + c + d
}
