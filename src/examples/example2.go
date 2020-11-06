// Program 2: Vypocet faktorialu (rekurzivne)
package main



func main() {
  print("Zadejte cislo pro vypocet faktorialu: ")
  a := 0
  err := 0
  a, err = inputi()
  if err = 0 {
    if a < 0 {
      print("Faktorial nejde spocitat!", "\n")
    } else {
      vysl := 0
      vysl = factorial(a)
      print("Vysledek je ", vysl, "\n")
    }
  } else {
    print("Chyba pri nacitani celeho cisla!\n")
  }
}
