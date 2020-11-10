// IFJ20: Ukazka prekryti promenne y a upozorneni na nebezpeci prekryti iteracni promenne i

package main

func main() {
	y := 20
	e := 4
	if 1 = 1 {
		y := 10
		print(y)
	} else {
		y := 3
		print(y)
	}
	for i := 1; i < 10; {
		print(i)
		s := 3
		i = i + 5 // POZOR na i := i + 5, nekonecna smycka
	}
	print(y)
}
