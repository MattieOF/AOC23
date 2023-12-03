package main

import (
	"bufio"
	"fmt"
	"os"
	"runtime"
	"slices"
	"strconv"
	"unicode"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func makeEngineMap(input *os.File) (int, [][]rune) {
	scanner := bufio.NewScanner(input)
	scanner.Scan()
	firstLine := scanner.Text()
	lineLength := len(firstLine)
	engineMap := make([][]rune, 1)
	engineMap[0] = []rune(firstLine)

	for scanner.Scan() {
		engineMap = append(engineMap, []rune(scanner.Text()))
	}

	check(scanner.Err())

	return lineLength, engineMap
}

func makeEngineMap2(input *os.File) (int, [][]*EngineMapElement) {
	scanner := bufio.NewScanner(input)
	lineLength := 0
	engineMap := make([][]*EngineMapElement, 1)

	i := 0
	for scanner.Scan() {
		// Insane amounts of allocations lmao don't think abt it
		if i == len(engineMap) {
			engineMap = append(engineMap, nil)
		}

		t := scanner.Text()
		lineLength = len(t)
		for _, char := range t {
			engineMap[i] = append(engineMap[i], &EngineMapElement{char, nil})
		}

		i++
	}

	check(scanner.Err())

	return lineLength, engineMap
}

func day1(input *os.File) {
	lineLength, engineMap := makeEngineMap(input)

	// This could be done easier and faster by checking if the ASCII code of the character is not '.' or a digit, so I'll do that instead
	// ... but I'll keep this here in case that doesn't work for some reason, since I've already written it
	// symbols := []rune{
	// 	'@',
	// 	'$',
	// 	'*',
	// 	'+',
	// 	'=',
	// 	'/',
	// 	'&',
	// 	'#',
	// 	'-',
	// }

	numBuffer := ""
	hasFoundSymbol := false
	total := 0
	for x := 0; x < len(engineMap); x++ {
		for y := 0; y < lineLength; y++ {
			fmt.Println("------", x, ",", y, "------")
			current := engineMap[x][y]
			if unicode.IsDigit(current) {
				numBuffer += string(current)
				if !hasFoundSymbol {
					// Check sorrounding runes for symbol
					for dx := max(0, x-1); dx <= min(len(engineMap)-1, x+1); dx++ {
						for dy := max(0, y-1); dy <= min(lineLength-1, y+1); dy++ {
							fmt.Println("dx:", dx, ", dy:", dy)
							if !unicode.IsDigit(engineMap[dx][dy]) && engineMap[dx][dy] != '.' {
								fmt.Println("Found symbol: " + string(engineMap[dx][dy]))
								hasFoundSymbol = true
								break
							}
						}
					}
				}
			}

			if !unicode.IsDigit(current) || y == lineLength-1 {
				if numBuffer != "" && hasFoundSymbol {
					fmt.Println("Adding: " + numBuffer)
					val, _ := strconv.Atoi(numBuffer)
					total += val
				}
				numBuffer = ""
				hasFoundSymbol = false
			}
		}
	}

	fmt.Println(total)
}

type EngineMapElement struct {
	value           rune
	relevantElement *Element
}

type Element struct {
	value       string
	adjacencies []*Element
}

func day2(input *os.File) {
	_, engineMap := makeEngineMap2(input)

	var elements []*Element
	var current *Element
	numBuffer := ""
	// hasFoundSymbol := false

	for y, row := range engineMap {
		for x, element := range row {
			if unicode.IsDigit(element.value) {
				numBuffer += string(element.value)

				if current == nil {
					current = &Element{numBuffer, nil}
				} else {
					current.value = numBuffer
				}

				for dy := max(0, y-1); dy <= min(len(engineMap)-1, y+1); dy++ {
					for dx := max(0, x-1); dx <= min(len(row)-1, x+1); dx++ {
						// fmt.Println(dx, dy)
						val := engineMap[dy][dx]
						if !unicode.IsDigit(val.value) && val.value != '.' {
							// hasFoundSymbol = true
							if val.value == '*' {
								if val.relevantElement == nil {
									e := Element{"*", nil}
									val.relevantElement = &e
									elements = append(elements, &e)
								}

								if !slices.Contains(val.relevantElement.adjacencies, current) {
									val.relevantElement.adjacencies = append(val.relevantElement.adjacencies, current)
								}
								if !slices.Contains(current.adjacencies, val.relevantElement) {
									current.adjacencies = append(current.adjacencies, val.relevantElement)
								}
							}
						}
					}
				}
			}

			if !unicode.IsDigit(element.value) || x == len(row)-1 {
				numBuffer = ""
				if current != nil {
					elements = append(elements, current)
				}
				current = nil
				// hasFoundSymbol = false
			}
		}
	}

	total := 0
	for _, element := range elements {
		// fmt.Println(element.value)

		if element.value == "*" && len(element.adjacencies) == 2 {
			num1, _ := strconv.Atoi(element.adjacencies[0].value)
			num2, _ := strconv.Atoi(element.adjacencies[1].value)
			total += num1 * num2
		}
	}

	fmt.Println("Total gear ratios:", total)
}

func main() {
	inputFile, err := os.Open("input.txt")
	check(err)

	day2(inputFile)

	var stats runtime.MemStats
	runtime.ReadMemStats(&stats)
	fmt.Println("allocated", stats.HeapAlloc, "bytes")
	fmt.Println("done", stats.Mallocs, "mallocs")
}
