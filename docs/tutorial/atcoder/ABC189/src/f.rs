use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        k: usize,
        a: [usize; k],
    }

    let mut broken = vec![false; n + 1];
    for i in a {
        broken[i] = true;
    }

    let mut prob_exp = vec![0.0; n + 1];
    let mut prob = vec![0.0; n + 1];
    prob[0] = 1.0;

    let mut prob_sum: f64 = 1.0;
    let mut exp_sum: f64 = 0.0;

    if m >= n {
        let goal_pct = (m - n + 1) as f64 / m as f64;
        prob[n] += prob[0] * goal_pct;
        prob_exp[n] += (prob_exp[0] + prob[0]) * goal_pct;
    }

    let mut prob_exp_fail = 0.0;

    for i in 1..n {
        prob[i] = prob_sum / m as f64;
        prob_exp[i] = prob[i] + exp_sum / m as f64;
        if !broken[i] {
            prob_sum += prob[i];
            exp_sum += prob_exp[i];
            if i + m >= n {
                let goal_pct = (i + m - n + 1) as f64 / m as f64;
                prob[n] += prob[i] * goal_pct;
                prob_exp[n] += (prob_exp[i] + prob[i]) * goal_pct;
            }
        } else {
            prob_exp_fail += prob_exp[i];
        }
        if i >= m && !broken[i - m] {
            prob_sum -= prob[i - m];
            exp_sum -= prob_exp[i - m];
        }
    }

    if prob[n] < 1e-8 {
        println!("-1");
    } else if (prob[n] - 1.0).abs() < 1e-8 {
        println!("{}", prob_exp[n]);
    } else {
        let exp_fail = prob_exp_fail / (1.0 - prob[n]);
        println!("{}", prob_exp[n] + (1.0 - prob[n]) * (prob_exp[n] + exp_fail) / prob[n]);
    }
}
