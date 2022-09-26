function updateNumberBox(val){
  document.getElementById("numberbox").value = val;
}

function updateSlider(val){
  document.getElementById("tankslider").value = val;
}

function sendPos(val){
  console.log(val);
}

function updateTankOne(val){
  var sceneEl=document.querySelector('a-scene');
  var tankV=sceneEl.querySelector('#tankpointer');
  var nVal = String(val+"cm");
  console.log(nVal);
  tankV.setAttribute('value', nVal);
  tankV.setAttribute('position',{x:4,y:0, z:(((-0.22583*val))+7.475)});
}