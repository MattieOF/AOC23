package A

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

func day1_a() {
	inputFile, err := os.Open("input.txt")
	check(err)

	var calibrations []string
	scanner := bufio.NewScanner(inputFile)

	for scanner.Scan() {
		line := scanner.Text()
		hasFoundNumber := false
		firstDigit := '0'
		lastDigit := '0'
		for _, ch := range line {
			if unicode.IsDigit(ch) {
				if hasFoundNumber {
					lastDigit = ch
				} else {
					firstDigit = ch
					lastDigit = ch
					hasFoundNumber = true
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
