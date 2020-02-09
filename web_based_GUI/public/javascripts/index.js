$(document).ready(function(){
        //set pod-status to safe to approach.
        localStorage.setItem('pod-status', 2);
});

$('#emerg-stop').click(function(){
        localStorage.setItem('pod-status', 0);
});

$('#ready-launch').click(function(){
        localStorage.setItem('pod-status', 1);
});

$('#safe-approach').click(function(){
        localStorage.setItem('pod-status', 2);
});

setInterval(function(){
        $.post('/send-status', {status: localStorage.getItem('pod-status')});
}, 1000);