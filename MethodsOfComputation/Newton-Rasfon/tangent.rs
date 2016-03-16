
fn foo(x: f32) -> f32 {
	return x * x - 5.0 * x + 3.0
	//return 4.0 - x.exp() - 2.0*x*x
    //return x.cos() - x + 1.0
}

fn dfoo(x :f32) -> f32{
	return 2.0*x - 5.0
	//return -x.exp() - 4.0*x
	//return -(x.sin()) - 1.0
}

fn main() {
    let mut n = 0;
    let eps = 0.01;
    let mut x = 0.0; // x0
    let mut tmp: f32;

    loop {
    	tmp = x;
    	x = tmp - foo(tmp)/dfoo(tmp);
    	n += 1;
    	let d = x - tmp;
    	if d.abs() < eps {
    	    break
    	}
    }
    print!("N = {:?}\n x = {:?}", n, x);
}