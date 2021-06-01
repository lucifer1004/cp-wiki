use proconio::input;

fn main() {
    input! {
        n: usize,
        mut k: usize,
        mut friends: [(usize, usize); n],
    }

    friends.sort();
    let mut now = 0;
    for (friend, money) in friends {
        if now + k < friend {
            break;
        }
        k -= friend - now;
        k += money;
        now = friend;
    }

    println!("{}", now + k);
}
