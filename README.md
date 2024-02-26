# Парсер математических выражений
Он умеет математику

## Основные функции/типы данных

### MathParser::parseExpression(expr)
Возвращает пойнтер на MathParser::Base_AST (или nullptr если что-то пошло не так)

### MathParser::solveExpression(expr)
Напрямую возвращает результат выражения

### MathParser::Exception
Тип исключенияпробрасваемый в MathParser::parseExpression и MathParser::solveExpression

## Поддерживаемые функции
- Арифметика (+, -, *, / и ^)
- Модуль (%, mod и mod(a, b))
- Корни (sqrt(x), cbrt(x), root(n, x))
- Тригонометрия:
    - Обычная (sin, cos, и т.п.)
    - Гиперболическая (sinh, cosh, и т.п.)
    - Обратная (arcsin/asin, arsinh, arcosh, atan2(y, x), и т.п.)
- Логарифмы (ln(x), lg(x), log(b, x))
- Комбинаторика (ncr(a, b), npr(a, b))

## Поддерживаемые константы
- pi (Ну камон) = 3.1415926...
- tau (pi * 2) = 6.2831855...
- phi (Золотое сечение) = 1.6180339...
- c (Скорость света в вакууме) = 299792458
- G (Гравитационная постоянная Ньютона) = 6.6743015 e-11
- g (Ускорение свободного падения на Земле) = 9.80665
- Mp (Масса протона) = 1.6726219... e-27
- Mn (Масса нейтрона) = 1.6749274... e-27



# Math Parser
It knows how to do math.

## Main functions/data types

### MathParser::parseExpression(expr)
It returns a MathParser::Base_AST pointer (or nullptr if something went wrong) based on the equation

### MathParser::solveExpression(expr)
Directly evaluates the expression

### MathParser::Exception
Is an exception type thrown by MathParser::parseExpression and MathParser::solveExpression

## Supported math operations
- Arithmetic operations (+, -, *, / and ^)
- Modulo operator (%, mod or mod(a, b))
- Roots (sqrt(x), cbrt(x), root(n, x))
- Trigonometry:
    - Regular (sin, cos, etc.)
    - Hyperbolic (sinh, cosh, etc.)
    - Inverted (arcsin/asin, arsinh, arcosh, atan2(y, x), etc.)
- Logarithms (ln(x), lg(x), log(b, x))
- Combination (ncr(a, b), npr(a, b))

## Supported constants
- pi (You know what it is) = 3.1415926...
- tau (pi * 2) = 6.2831855...
- phi (The golden ratio) = 1.6180339...
- c (The speed of light in vaccuum) = 299792458
- G (Newton's gravitational constant) = 6.6743015 e-11
- g (Earth's free fall acceleration) = 9.80665
- Mp (The mass of a proton) = 1.6726219... e-27
- Mn (The mass of a neutron) = 1.6749274... e-27
