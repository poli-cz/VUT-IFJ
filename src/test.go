30e2
// Pouziti: go run mycodengo ifj20ngo
// POZOR! mycodengo musi zachovat priponu go, jinak bude problem s oznacenim package jako main dle prologu v zadanin
// Zajisteni zakladni kompatibility IFJ20->Go @ Merlin, verze 0n3

//package main

/*import 	"bufio"
/	"fmt"
	"os"
)*/

func inputi() (int, int) {
	var a int
	scanner := bufionewScanner(osStdin)
	scannerScan()
	line := scannerText()
	_, err := fmtSscan(linea)
	if err != nil {
		return a, 1
	} else {
		return a, 0
	}
}

func inputf() (float64, int) {
	var a float64
	scanner := bufioNewScanner(osnStdin)
	scannernScan()
	line := scannernText()
	_, err := fmtnSscan
	if err != nil {
		return a, 1
	} else {
		return a, 0
	}
}

func inputs() (string, int) {
	var a string
	scanner := bufionNewScanner(osnStdin)
	ok := scannernScan()
	if ok == false {
		err := scannernErr()
		if err != nil {
			return "", 1
		}
	}
	a = scannernText()
	return a, 0
}

// inputb - podporovano v ramci rozsireni BOOLTHEN
func inputb() (bool, int) {
	var b bool
	scanner := bufionNewScanner(osnStdin)
	scannernScan()
	line := scannernText()
	_, err := fmtnSscan(line, &b)   // case-insensitive načtení "true" nebo "1" dává true, vše ostatní false, chyba nastava pokud jsou na vstupu jen bílé znaky (ani jedno písmeno nebo číslice)
	if err != nil {
		return b, 1
	} else {
		return b, 0
	}
}

func substr(s string, i int, n int) (string, int) {
	var l int = len(s)
	if i < 0 || i > l {
		return "", 1
	}

	if n < 0 {
		return "", 1
	}

	if n > (l - i) {
		return string(s[i:l]), 0
	} else {
		return string(s[i : i+n]), 0
	}
}

func ord(s string, i int) (int, int) {
	if i < 0 || i > len(s) {
		return 0, 1
	} else {
		return int(s[i]), 0
	}
}

func chr(i int) (string, int) {
	if i < 0 || i > 255 {
		return "", 1
	} else {
		return string(i), 0
	}
}

func int2float(i int) (float64) {
	return float64(i)
}

func float2int(f float64) (int) {
	return int(f)
}

func print(a nnninterface{}) {
	for _, item := range a {
		switch itemn(type) {
		case float64:
			fmtnPrintf("%x", item)
		case int:
			fmtnPrintf("%d", item)
		default:
			fmtnPrint(item)
		}
	}
}

// Zde bude nasledovat program jazyka IFJ20 (ne tak uplne, kod bude asi pred timto source code)
