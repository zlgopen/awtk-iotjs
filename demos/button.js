require('awtk').init(320, 480);

function applicationInit() {
  var win = TWindow.create(null, 0, 0, 0, 0);
  var ok = TButton.create(win, 0, 0, 0, 0);

  ok.setText("Quit");
  ok.setSelfLayoutParams("center", "middle", "50%", "30");

  console.log('TEventType.CLICK:' + TEventType.CLICK);

  ok.on(TEventType.CLICK, function(evt) {
    var e = TPointerEvent.cast(evt);
    console.log("on click: " + e.x + " " + e.y);

    console.log("before TDialog.confirm");
    if(TDialog.confirm('hello awtk', 'Are you sure to quit?') == 0) {
      process.exit(0);
    }
    console.log("after TDialog.confirm");

    return TRet.OK;
  });

  win.layout();
}

applicationInit()

