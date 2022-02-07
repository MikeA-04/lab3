use std::process;
use std::fs::File;
use std::ffi::{CString};
use nix::sys::wait::{wait};
use nix::unistd::ForkResult::{Child, Parent};
use nix::unistd::{execv, fork, Pid, getpid};
use std::io::prelude::*;
use std::str;

fn string_to_cstring_vector(args: &str)->Vec<CString> {
    let comm:Vec<&str> = args.split_whitespace().collect();    
    let comm_args:Vec<CString> = comm.into_iter().map(|x| CString::new(x).unwrap()).collect();
    return comm_args;
}

fn file_read_error(pid:Pid)->String{
    let err_msg = "failed to read announcement with pid ".to_string();
    let pid_string = pid.to_string();
    let mut fileread_error = String::new();
    fileread_error += &err_msg;
    fileread_error += &pid_string;
    return fileread_error;
}

fn main() {
    let args:Vec<CString> = string_to_cstring_vector("/bin/echo Hello CS361");
    let mut vec_str = [0; 16];
    //Opening File
    let mut file = File::open("announcement.txt").expect("announcement.txt cannot be opened");
    println!("Parent Process ID: {}", getpid());
  
  unsafe {
    let pid = fork();
    match pid {
      //To-Do 2: Add the condition so that following block will be executed by child process alone
      Ok(/*Condition*/) => {
        
        file.read(&mut vec_str).expect(file_read_error(getpid()).as_str());
        println!("announcement with pid {}: {:?}", getpid(),str::from_utf8(&vec_str).unwrap());
        
        //drop(file);

        file.read(&mut vec_str).expect(file_read_error(getpid()).as_str());
        println!("announcement with pid {}: {:?}", getpid(),str::from_utf8(&vec_str).unwrap());

        //To-Do 4: Override child process to execute command in args

        file.read(&mut vec_str).expect(file_read_error(getpid()).as_str());
        println!("announcement with pid {}: {:?}", getpid(),str::from_utf8(&vec_str).unwrap());
        
        process::exit(1);
      }

      //To-Do 2.5: Add the condition so that following block will be executed by parent process
      //alone
      Ok(/*Condition*/) => {

        //To-Do 3: Make sure that Child process has finished execution before moving forward
        
        file.read(&mut vec_str).expect(file_read_error(getpid()).as_str());
        println!("announcement with pid {}: {:?}", getpid(),str::from_utf8(&vec_str).unwrap());
      },

      //To-Do 1: Add the condition to handle fork failure,
      //Message to be displayed after failure detection: "Fork Failed: Unable to create child process!"
    }
  }
  println!("Exiting Parent Process");
}
