$(document).ready(function(){
    $('#leitura_rfid').click(function(){
        $.ajax({
            url: '{% url "leitura_rfid" %}',
            method:'GET',
            success: function(data){
                $('#rfid').text(data.result);
            },
            error: function(xhr, status, error) {
                $('#rfid').text('Ocorreu um erro: ' + error);
            }
        });
    });
});