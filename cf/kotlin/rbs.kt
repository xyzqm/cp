fun main() {
    val input = readln()

    val matchingOpen = mapOf(
        '>' to '<',
        '}' to '{',
        ']' to '[',
        ')' to '('
    )
    val openBrackets = setOf('<', '{', '[', '(')

    var swaps = 0
    val stack = ArrayDeque<Char>()

    for (c in input) {
        when {
            c in openBrackets -> stack.addLast(c)
            stack.isEmpty() -> {
                println("Impossible")
                return
            }
            else -> {
                if (stack.last() != matchingOpen[c]) swaps++
                stack.removeLast()
            }
        }
    }

    println(if (stack.isEmpty()) swaps.toString() else "Impossible")
}
