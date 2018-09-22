
function shuffle(array) {
    var m = array.length, t, i;

    // While there remain elements to shuffle…
    while (m) {

        // Pick a remaining element…
        i = Math.floor(Math.random() * m--);

        // And swap it with the current element.
        t = array[m];
        array[m] = array[i];
        array[i] = t;
    }

    return array;
}

jQuery(document).ready(function(){
    shuffle($('.hat')).slice(0,1).show();
    $('.copyright').empty().append("&copy; 2017-2018 G. Eusebio");
});