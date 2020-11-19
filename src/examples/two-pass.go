// IFJ20: Ukazka volani funkce f pred jeji definici

package main

func g() {
	j := 0
	print(j)
	j = f(3)
	print(j)
	f(j)
}

func f(i int) (int) {
	print(i)
	return i
}

func main() {
  g()
}
