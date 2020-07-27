fun readInts(): List<Int> {
    return readLine()!!.split(" ").map(String::toInt)
}

class SegmentTree(private val a: List<Int>) {
    private val len = a.size * 4
    private val s = LongArray(len)

    private fun calc(idx: Int) {
        s[idx] = s[idx shl 1].coerceAtMost(s[idx shl 1 xor 1])
    }

    fun build(idx: Int, l: Int, r: Int) {
        if (l == r)
            s[idx] = a[l - 1].toLong()
        else {
            val mid = (l + r) shr 1
            build(idx shl 1, l, mid)
            build(idx shl 1 xor 1, mid + 1, r)
            calc(idx)
        }
    }

    fun update(idx: Int, pos: Int, v: Int, cl: Int, cr: Int) {
        if (cl == pos && cl == cr) {
            s[idx] = v.toLong()
            return
        }
        val mid = (cl + cr) shr 1
        if (pos <= mid)
            update(idx shl 1, pos, v, cl, mid)
        else
            update(idx shl 1 xor 1, pos, v, mid + 1, cr)
        calc(idx)
    }

    fun query(idx: Int, l: Int, r: Int, cl: Int, cr: Int): Long {
        if (cl >= l && cr <= r)
            return s[idx]
        var ans = Long.MAX_VALUE
        val mid = (cl + cr) shr 1
        if (l <= mid)
            ans = ans.coerceAtMost(query(idx shl 1, l, r, cl, mid))
        if (mid < r)
            ans = ans.coerceAtMost(query(idx shl 1 xor 1, l, r, mid + 1, cr))
        return ans
    }
}

fun main() {
    val (n, m) = readInts()
    val st = SegmentTree(readInts())
    st.build(1, 1, n)
    val ans = mutableListOf<String>()
    for (i in 0 until m) {
        val (op, v1, v2) = readInts()
        if (op == 1)
            st.update(1, v1 + 1, v2, 1, n)
        else
            ans.add(st.query(1, v1 + 1, v2, 1, n).toString())
    }
    println(ans.joinToString("\n"))
}
