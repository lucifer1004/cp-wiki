use proconio::input;
use proconio::marker::Chars;

fn main() {
    input! {
        s: Chars,
    }
    println!("{}", if s[0] == s[1] && s[1] == s[2] {"Won"} else {"Lost"});
}
