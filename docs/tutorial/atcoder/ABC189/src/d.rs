use proconio::input;

fn main() {
    input! {
        n: usize,
        s: [String; n],
    }

    let mut f = 1u64;
    let mut t = 1u64;

    for si in s {
        if si == "AND" {
            let nf = f * 2 + t;
            let nt = t;
            f = nf;
            t = nt;
        } else {
            let nf = f;
            let nt = t * 2 + f;
            f = nf;
            t = nt;
        }
    }

    println!("{}", t);
}
