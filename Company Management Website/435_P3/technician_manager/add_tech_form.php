<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>
    <h1>Add Technician</h1>
    <form action="add_tech.php" method="post">
        <label for='fName'>First Name:</label>
        <input type='text' name='fName'> <br><br>

        <label for='lName'>Last Name:</label>
        <input type='text' name='lName'> <br><br>

        <label for='email'>Email:</label>
        <input type='text' name='email'> <br><br>

        <label for='phone'>Phone:</label>
        <input type='text' name='phone'> 
        <span>Use XXX-XXX-XXXX format.</span><br><br>

        <label for='password'>Password:</label>
        <input type='text' name='password'> 
        <span>Use no spaces.</span><br><br>

        <input type='submit'value='Add Technician'>
    </form>

    <br><a href='index.php'>View Technician List</a>
</main>

<?php include '../view/footer.php'; ?>