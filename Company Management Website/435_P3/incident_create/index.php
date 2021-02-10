<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>
    <h1>Get Customer</h1>

    <p> You must enter the customer's email address to select the customer</p>

    <form action="create_incident_form.php" method="post">
        <label for='email'>Email:</label>
        <input type='text' name='email'>
        <input type='submit'value='Get Customer'>
    </form>
</main>

<?php include '../view/footer.php'; ?>