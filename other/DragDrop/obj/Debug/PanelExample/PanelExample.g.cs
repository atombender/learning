﻿#pragma checksum "..\..\..\PanelExample\PanelExample.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "8F53C9F05B29C34751EB28B6026BD83F"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using DnD;
using Samples.DragDrop;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace Samples.DragDrop {
    
    
    /// <summary>
    /// PanelExample
    /// </summary>
    public partial class PanelExample : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 22 "..\..\..\PanelExample\PanelExample.xaml"
        internal System.Windows.Controls.Grid _mainGrid;
        
        #line default
        #line hidden
        
        
        #line 33 "..\..\..\PanelExample\PanelExample.xaml"
        internal System.Windows.Controls.WrapPanel _topPanel;
        
        #line default
        #line hidden
        
        
        #line 62 "..\..\..\PanelExample\PanelExample.xaml"
        internal System.Windows.Controls.WrapPanel _bottomPanel;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/Samples.DragDrop;component/panelexample/panelexample.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\PanelExample\PanelExample.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal System.Delegate _CreateDelegate(System.Type delegateType, string handler) {
            return System.Delegate.CreateDelegate(delegateType, this, handler);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this._mainGrid = ((System.Windows.Controls.Grid)(target));
            return;
            case 2:
            this._topPanel = ((System.Windows.Controls.WrapPanel)(target));
            return;
            case 3:
            this._bottomPanel = ((System.Windows.Controls.WrapPanel)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
