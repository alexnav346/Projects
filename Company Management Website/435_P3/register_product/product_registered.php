<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<?php 
$theProduct = $_POST['theProduct'];
$theCustomerID = $_POST['customerID'];
?>

<?php
        $productQuery = 'SELECT * FROM products WHERE productCode ="' . $theProduct . '"';
        $queryExec = $db->prepare($productQuery);
        $queryExec->execute();
        $productInfo = $queryExec->fetch();

        $queryExec->closeCursor();
?>

<?php
    $addQuery = 'INSERT INTO registrations VALUES( :custID, :prodCode, NOW() )';
    $addQuery = $db->prepare($addQuery);
    $addQuery->bindValue(':custID', $theCustomerID);
    $addQuery->bindValue(':prodCode', $theProduct);
    $response = $addQuery->execute();
    $addQuery->closeCursor();
?>


<main>

    <h1>Register Product</h1> <br>

    <span>Product <?php echo $productInfo['name']?> was registered succefully.</span> <br>

</main>


<?php include '../view/footer.php'; ?>