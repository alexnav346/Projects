<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>
    <?php
        $productQuery = 'SELECT * FROM products';
        $queryExec = $db->prepare($productQuery);
        $queryExec->execute();
        $allProducts = $queryExec->fetchAll();

        $queryExec->closeCursor();
    ?>

    <h1>Product List</h1>
    <table>
        <tr>
            <th>Code</th>
            <th>Name</th>
            <th>Version</th>
            <th>Release Date</th>
            <th>Options</th>
        </tr>
        
        <?php
            foreach ($allProducts as $product)
            {
                echo 
                    '<tr>' .
                    '<td>' . $product['productCode'] . '</td>' .
                    '<td>' . $product['name'] . '</td>' . 
                    '<td>' . $product['version'] . '</td>' . 
                    '<td>' . $product['releaseDate'] . '</td>' .
                    '<td>' . 
                        '<form action="delete_product.php" method="post"> ' .
                            '<input type="hidden" name="product_id" value="' . $product['productCode'] . '">' .
                            '<input type="submit" value="Delete"> ' .
                        '</form> </td>' .
                    '</tr>';
            }
        ?>
    </table>

    <br><a href='add_product_form.php'>Add Product</a>
    
</main>

<?php include '../view/footer.php'; ?>