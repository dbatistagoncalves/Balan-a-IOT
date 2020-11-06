<?php
    
    include "conexao.php";

    $sensor1_recebido = $_GET['Peso']; //peso é um ponteiro que repassa o valor do sensor tecebido 
	//echo "Peso recebido:" . $sensor1_recebido;
    $SQL_INSERT = "INSERT INTO tbsensores (peso) VALUES (:P)";
    $stmt = $conexao->prepare($SQL_INSERT);
    $stmt->bindParam(":P",$sensor1_recebido);

    if($stmt->execute()){
        
        echo "inset_ok";
        
    }else{
        echo "insert_erro";
    }
?>