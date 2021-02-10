<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<?php $theEmail = $_POST['email']; 
        $continue = false;?>

<?php
        $customerQuery = 'SELECT * FROM customers WHERE email ="' . $theEmail . '"';
        $queryExec = $db->prepare($customerQuery);
        $queryExec->execute();
        $theCustomer = $queryExec->fetch();

        $queryExec->closeCursor();

        $error = "Email Address Not Found in Database.";

        if (empty($theCustomer))
        {
            include('../errors/error.php');
        }           
?>

<?php
        $productQuery = 'SELECT * FROM products';
        $queryExec = $db->prepare($productQuery);
        $queryExec->execute();
        $theProducts = $queryExec->fetchAll();

        $queryExec->closeCursor();
?>

<main>


    <h1>Register Product</h1> <br>

    <form action="product_registered.php" method="post">
        <label for="customerName">Customer:   </label>
        <input type="text" id="customerName" name="customerName" value="<?php echo $theCustomer['firstName'] . ' ' . $theCustomer['lastName'] ?>" readonly>
        <br><br>
        <label for="theProduct">Product:   </label>

        <select name="theProduct" id="theProduct">
        
            <?php
                foreach ($theProducts as $product)
                {
                    echo '<option value="' . $product['productCode'] . '">';
                    echo $product['name'] . '</option>';
                }
            ?>

        </select>

        <br><br>
        <input type="hidden" name="customerID" value="<?php echo $theCustomer['customerID']?>">
        <input type="submit" value="Register Product">
    </form>


</main>


<?php include '../view/footer.php'; ?>