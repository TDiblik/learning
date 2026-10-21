Basic:
- `CXX = ` => specifikace compileru
- `CXXFLAGS = ` => specifikace flagů compileru
- `$(some-command)` => subcommand
- `$(proměnná)` => získaní hodnoty nějaké proměnné, např. `$(CXX)` - získá hodnotu CXX proměnné
`CXX = g++` => nastavení CXX na hodnotu `g++`
- `VAR = $(shell some-command)` => provolání commandu v shellu a uložení promměné do hodnoty
- `ifeq (value,value) .... endif` => if podmínka která porovná levou a pravou stranu
- `ifeq ($(and $(var1), $(var2)), some-value)` => if podmínka která porovná všechny hodnoty vůči sobě.
- Když v targetu začnu psát `@` executenu command v shellu, takže např. `@mkdir abc` vytvoří directory až se tam script dostane

Targety:
`.PHONY: all build ...` => specifikace targetů které nemají equivalentní názvy souborů
`all: ` => specifikace custom targetu
