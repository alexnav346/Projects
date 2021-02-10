<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>
    <h1>Add Product</h1>
    <form action="add_product.php" method="post">
        <label for='prodCode'>Code:</label>
        <input type='text' name='prodCode'> <br><br>

        <label for='prodName'>Name:</label>
        <input type='text' name='prodName'> <br><br>

        <label for='prodVersion'>Version:</label>
        <input type='text' name='prodVersion'> <br><br>

        <label for='prodDate'>Release Date:</label>
        <input type='text' name='prodDate'> 
        <span>Use 'yyyy-mm-dd' format.</span><br><br>

        <input type='submit'value='Add Product'>
    </form>

    <br><a href='index.php'>View Product List</a>
</main>

<?php include '../view/footer.php'; ?>