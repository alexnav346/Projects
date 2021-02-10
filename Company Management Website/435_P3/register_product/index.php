<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>

    <h1>Customer Login</h1> <br>

    <span>You must enter login before you can register a product.</span>
    <br><br>

    <form action="register_product_page.php" method="post">
        <label for="email">Email:   </label>
        <input type="text" id="email" name="email">
        <input type="submit" value="Login">
    </form>

</main>

<?php include '../view/footer.php'; ?>