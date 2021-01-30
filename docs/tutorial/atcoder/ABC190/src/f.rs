use proconio::input;

fn low_bit(x: i32) -> i32 {
    x & (-x)
}

struct FenwickTree {
    v: Vec<i32>
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        FenwickTree {
            v: vec![0; n + 1],
        }
    }

    fn update(&mut self, mut x: usize, val: i32) {
        while x < self.v.len() {
            self.v[x as usize] += val;
            x += low_bit(x as i32) as usize;
        }
    }

    fn query(&mut self, mut x: usize) -> i32 {
        let mut ans = 0;
        while x > 0 {
            ans += self.v[x as usize];
            x -= low_bit(x as i32) as usize;
        }
        ans
    }
}



fn main() {
    input! {
        n: usize,
        a: [usize; n],
    }

    let mut ft = FenwickTree::new(n);
    let mut ans = vec![0i64; n];
    for i in 0..n {
        let larger = (i as i32) - ft.query(a[i] + 1);
        ans[0] += larger as i64;
        ft.update(a[i] + 1, 1);
    }

    println!("{}", ans[0]);
    for i in 1..n {
        ans[i] = ans[i - 1] - a[i - 1] as i64 + (n as i64 - 1 - a[i - 1] as i64);
        println!("{}", ans[i]);
    }
}
