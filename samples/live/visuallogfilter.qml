import QtQuick 2.3
import live 1.0

Row{
    anchors.fill: parent
    
    // This sample shows the usage of log filters on livecv's log
    // to sort out data into different categories
    
    // You can use regular expressions or strings to match
    // each log entry
        
    VisualLogView{
        width: parent.width / 2
        height: parent.height
        backgroundColor: '#191017'
        model: VisualLogFilter{
            id: logFilter
            source: livecv.log
            search: /Output\s[0-9]{1}$/
        }
    }
       
    VisualLogView{
        width: parent.width / 2
        height: parent.height
        model: VisualLogFilter{
            id: logFilter2
            source: livecv.log
            search: "Output 1"
        }
    }

    Component.onCompleted: {
        livecv.log.clearValues()
        for ( var i = 0; i < 5; ++i )
            console.log("Output " + i);
        for ( var i = 10; i < 15; ++i )
            console.log("Output " + i);
    }
}