use rand;

fn main() {
    // let question = requestty::Question::expand("overwrite")
    // .message("Conflict on `file.rs`")
    // .choices(vec![
    //     ('y', "Overwrite"),
    //     ('a', "Overwrite this one and all next"),
    //     ('d', "Show diff"),
    // ])
    // .default_separator()
    // .choice('x', "Abort")
    // .build();

    // println!("{:#?}", requestty::prompt_one(question));
    let mut rng = rand::thread_rng();
    let device_id = rand::distributions::Alphanumeric.sample_string(&mut rng, 16).to_uppercase();

    println!("hello world");
}
