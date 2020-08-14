import kotlin.math.*

fun readInts(): List<Int> {
    return readLine()!!.trim().split(" ").map(String::toInt)
}

fun nearest(n: Int): Int {
    return 1.shl(ceil(log2(n.toDouble())).toInt() + 1)
}

data class Complex(val real: Double, val imag: Double) {
    operator fun plus(other: Complex): Complex {
        return Complex(real + other.real, imag + other.imag)
    }

    operator fun minus(other: Complex): Complex {
        return Complex(real - other.real, imag - other.imag)
    }

    operator fun times(other: Double): Complex {
        return Complex(real * other, imag * other)
    }

    operator fun times(other: Complex): Complex {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real)
    }
}

val rev = IntArray(nearest(1000002))

fun change(f: Array<Complex>, n: Int) {
    if (rev[1] == 0)
        for (i in 0 until n) {
            rev[i] = rev[i shr 1] shr 1
            if (i % 2 == 1)
                rev[i] = rev[i] or (n shr 1)
        }
    for (i in 0 until n)
        if (i < rev[i]) {
            val tmp = f[i]
            f[i] = f[rev[i]]
            f[rev[i]] = tmp
        }
}

fun fft(f: Array<Complex>, n: Int, rev: Int) {
    change(f, n)
    var len = 2
    while (len <= n) {
        val omega = Complex(cos(2.0 * PI / len * rev), sin(2.0 * PI / len * rev))
        var l = 0
        while (l < n) {
            var now = Complex(1.0, 0.0)
            for (i in l until l + len / 2) {
                val g = f[i]
                val h = now * f[i + len / 2]
                f[i] = g + h
                f[i + len / 2] = g - h
                now *= omega
            }
            l += len
        }
        len *= 2
    }
    if (rev == -1)
        for (i in 0 until n)
            f[i] = f[i] * (1.0 / n)
}

fun main() {
    val (n, m) = readInts()
    val k = nearest(n + m + 1)
    val a = Array(k) { Complex(0.0, 0.0) }
    for ((i, v) in readInts().withIndex())
        a[i] = Complex(v.toDouble(), 0.0)
    val b = Array(k) { Complex(0.0, 0.0) }
    for ((i, v) in readInts().withIndex())
        b[i] = Complex(v.toDouble(), 0.0)
    fft(a, k, 1)
    fft(b, k, 1)
    for (i in 0 until k)
        a[i] = a[i] * b[i]
    fft(a, k, -1)
    val ans = a.slice(0 until n + m + 1).map { round(it.real).toInt() }
    println(ans.joinToString(" "))
}
