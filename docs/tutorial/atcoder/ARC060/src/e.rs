use proconio::input;

const K: usize = 18;

fn main() {
    input! {
        n: usize,
        x: [usize; n],
        l: usize,
        q: usize,
        queries: [(usize, usize); q],
    }

    let mut right = vec![vec![n; K]; n + 1];
    for i in 1..=n {
        let mut lo = i;
        let mut hi = n;
        while lo <= hi {
            let mid = (lo + hi) >> 1;
            let dist = x[mid - 1] - x[i - 1];
            if dist > l {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        right[i][0] = hi;
    }
    for k in 1..K {
        for i in 1..=n {
            if right[i][k - 1] < n {
                right[i][k] = right[right[i][k - 1]][k - 1];
            }
        }
    }

    let mut left = vec![vec![1usize; K]; n + 1];
    for i in 1..=n {
        let mut lo = 1usize;
        let mut hi = i;
        while lo <= hi {
            let mid = (lo + hi) >> 1;
            let dist = x[i - 1] - x[mid - 1];
            if dist > l {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        left[i][0] = lo;
    }
    for k in 1..K {
        for i in 1..=n {
            if left[i][k - 1] > 1 {
                left[i][k] = left[left[i][k - 1]][k - 1];
            }
        }
    }

    for (a, b) in queries {
        let mut acc = 0;
        let mut pos = a;
        if a < b {
            for k in (0..K).rev() {
                if right[pos][k] < b {
                    acc ^= 1 << k;
                    pos = right[pos][k];
                }
            }
            if pos != b {
                acc += 1;
            }
        } else {
            for k in (0..K).rev() {
                if left[pos][k] > b {
                    acc ^= 1 << k;
                    pos = left[pos][k];
                }
            }
            if pos != b {
                acc += 1;
            }
        }
        println!("{}", acc);
    }
}
