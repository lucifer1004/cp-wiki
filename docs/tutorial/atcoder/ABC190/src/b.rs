use proconio::input;

fn main() {
    input! {
        n: usize,
        s: usize,
        d: usize,
        spells: [(usize, usize); n],
    }

    for (x, y) in spells {
        if x < s && y > d {
            println!("Yes");
            return;
        }
    }

    println!("No");
}
