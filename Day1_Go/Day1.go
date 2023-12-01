package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func substr(input string, start int, length int) string {
	asRunes := []rune(input)

	if start >= len(asRunes) {
		return ""
	}

	if start+length > len(asRunes) {
		length = len(asRunes) - start
	}

	return string(asRunes[start : start+length])
}

func main() {
	inputFile, err := os.Open("input.txt")
	check(err)

	var calibrations []string
	scanner := bufio.NewScanner(inputFile)

	stringsToDigits := map[string]rune{
		"one":   '1',
		"two":   '2',
		"three": '3',
		"four":  '4',
		"five":  '5',
		"six":   '6',
		"seven": '7',
		"eight": '8',
		"nine":  '9',
	}

	for scanner.Scan() {
		line := scanner.Text()
		hasFoundNumber := false
		firstDigit := '0'
		lastDigit := '0'
		textBuffer := ""
		for _, ch := range line {
			if unicode.IsDigit(ch) {
				textBuffer = ""
				if hasFoundNumber {
					lastDigit = ch
				} else {
					firstDigit = ch
					lastDigit = ch
					hasFoundNumber = true
				}
			} else {
				textBuffer += string(ch)
				for i := 1; i < len(textBuffer)+1; i++ {
					sub := substr(textBuffer, len(textBuffer)-i, i)
					// fmt.Println(sub)
					digitRune, ok := stringsToDigits[sub]
					if ok {
						fmt.Println("FOUND")
						if hasFoundNumber {
							lastDigit = digitRune
						} else {
							firstDigit = digitRune
							lastDigit = digitRune
							hasFoundNumber = true
						}
						break
					}
				}
			}
		}
		calibrations = append(calibrations, string(firstDigit)+string(lastDigit))
		fmt.Printf("%s: %s\n", line, string(firstDigit)+string(lastDigit))
	}

	check(scanner.Err())

	total := 0
	for _, calibration := range calibrations {
		val, err := strconv.Atoi(calibration)
		check(err)
		total += val
	}

	fmt.Println(total)
}
