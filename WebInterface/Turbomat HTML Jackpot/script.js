
let port;
let reader;
let inputDone;
let outputDone;
let inputStream;
let outputStream;


$(document).ready(function() {


    $('#drinks').show();
    $('#message-board').hide();
    $('#leaderboard').hide();
    $('#party').hide();
    $('#butConnected').hide();

    $('#drinks-button').addClass('button-active');
    $('#theme').addClass('drinks-body');

    document.addEventListener('DOMContentLoaded', () => {
    });
    
    butReconnect.addEventListener('click', connect);
    
    async function connect() {
      port = await navigator.serial.requestPort();
      // - Wait for the port to open.
      await port.open({ baudRate: 9600 });
    
      const encoder = new TextEncoderStream();
      outputDone = encoder.readable.pipeTo(port.writable);
      outputStream = encoder.writable;
    
      writeToStream('\x03', 'ja');
      $('#butConnected').show();
      $('#butReconnect').hide();
    }
    
    butConnected.addEventListener('click', sendRed);
    
    function sendMessage(){
      writeToStream('\x03', 'ja');
    }
    
    function writeToStream(...lines) {
      const writer = outputStream.getWriter();
      lines.forEach((line) => {
        console.log('[SEND]', line);
        writer.write(line + '\n');
      });
      writer.releaseLock();
    }

    var wheelPicker = new iro.ColorPicker("#wheelPicker", {
      width: 600,
      color: "rgb(255,255,255)",
      borderWidth: 0,
      handleRadius: 24,
      borderColor: "#fff",
      layout: [
        {
          component: iro.ui.Wheel,
        },
      ]
    });

    async function sendRed() {
      writeToStream('\x03', 'red');
    }

    async function sendColor(){
      /*
      var redColor = wheelPicker.color.red;
      var greenColor = wheelPicker.color.green;
      var blueColor = wheelPicker.color.blue;

      var redSend = 'r' + redColor;
      var greenSend = 'g' + greenColor;
      var blueSend = 'b' + blueColor;

      writeToStream('\x03', redSend);
      setTimeout(function () {
        writeToStream('\x03', greenSend);
      }, 3000);
      setTimeout(function () {
        writeToStream('\x03', blueSend);
      }, 3000);
      */

      

      var hexWrite = wheelPicker.color.hexString;

      var hexSend = hexWrite.toString();

      hexSEnd = hexSend.substring(1);

      console.log(hexSend);

      writeToStream(hexSend);

    }
    

    $('#drinks-button').click((event) => {
        $('#drinks').show();
        $('#drinks-button').addClass('button-active');

        $('#message-board').hide();
        $('#message-button').removeClass('button-active');

        $('#leaderboard').hide();
        $('#leaderboard-button').removeClass('button-active');

        $('#party').hide();
        $('#party-button').removeClass('button-active');

        $('#theme').addClass('drinks-body');
        $('#theme').removeClass('message-body');
        $('#theme').removeClass('leaderboard-body');
        $('#theme').removeClass('party-body');
      });

      $('#message-button').click((event) => {
        $('#drinks').hide();
        $('#drinks-button').removeClass('button-active');

        $('#message-board').show();
        $('#message-button').addClass('button-active');

        $('#leaderboard').hide();
        $('#leaderboard-button').removeClass('button-active');

        $('#party').hide();
        $('#party-button').removeClass('button-active');

        $('#theme').removeClass('drinks-body');
        $('#theme').addClass('message-body');
        $('#theme').removeClass('leaderboard-body');
        $('#theme').removeClass('party-body');
      });
    
    $('#leaderboard-button').click((event) => {
        $('#drinks').hide();
        $('#drinks-button').removeClass('button-active');

        $('#message-board').hide();
        $('#message-button').removeClass('button-active');

        $('#leaderboard').show();
        $('#leaderboard-button').addClass('button-active');

        $('#party').hide();
        $('#party-button').removeClass('button-active');

        $('#theme').removeClass('drinks-body');
        $('#theme').removeClass('message-body');
        $('#theme').addClass('leaderboard-body');
        $('#theme').removeClass('party-body');
      });

    $('#party-button').click((event) => {
        $('#drinks').hide();
        $('#drinks-button').removeClass('button-active');

        $('#message-board').hide();
        $('#message-button').removeClass('button-active');

        $('#leaderboard').hide();
        $('#leaderboard-button').removeClass('button-active');

        $('#party').show();
        $('#party-button').addClass('button-active');

        $('#theme').removeClass('drinks-body');
        $('#theme').removeClass('message-body');
        $('#theme').removeClass('leaderboard-body');
        $('#theme').addClass('party-body');
      });

      $('#add-message').click(
            function(){
                var toAdd = $('input[name=ListItem]').val();
                 $('ul').prepend('<li>' + toAdd + '</li>');
            });
       
      $("input[name=ListItem]").keyup(function(event){
          if(event.keyCode == 13){
            $("#add-message").click();
          }         
      });
      
      $(document).on('dblclick','li', function(){
        $(this).toggleClass('strike').fadeOut('slow');    
      });
      
      $('input').focus(function() {
        $(this).val('');
      });

      $("form").keypress(function(e) {
        //Enter key
        if (e.which == 13) {
          return false;
        }
      });

      /*
	//Firebase configuration
	var firebaseConfig = {
	  apiKey: "AIzaSyCyUc4SSrO_AI33KyUUzIV4vanKXJBqBF4",
	  authDomain: "turbo-7d9e7.firebaseapp.com",
	  databaseURL: "https://turbo-7d9e7-default-rtdb.europe-west1.firebasedatabase.app",
	  projectId: "turbo-7d9e7",
	  storageBucket: "turbo-7d9e7.appspot.com",
	  messagingSenderId: "713745754210",
	  appId: "1:713745754210:web:4ab36141240b59d320c93b"
  };
  
	// Initialize Firebase
	firebase.initializeApp(firebaseConfig);

  var database = firebase.database();

  console.log("hello");
  console.log(database);

  function writeUserData(userId, name, email, imageUrl) {
    firebase.database().ref('users/' + userId).set({
      username: name,
      email: email,
      profile_picture : imageUrl
    });
  }

  writeUserData("abc","asf","casfg","ccasd");
  */
});