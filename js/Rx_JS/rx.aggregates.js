// Copyright (c) Microsoft Corporation.  All rights reserved.
// This code is licensed by Microsoft Corporation under the terms
// of the MICROSOFT REACTIVE EXTENSIONS FOR JAVASCRIPT AND .NET LIBRARIES License.
// See http://go.microsoft.com/fwlink/?LinkId=186234.

(function(){var a=this;var b;if(typeof ProvideCustomRxRootObject =="undefined")b=a.Rx; else b=ProvideCustomRxRootObject();var c=undefined;var d=function(l,m){return l===m;};var e=function(l){return l;};var f=b.Observable;var g=f.prototype;var h="Sequence contains no elements.";var i=f.CreateWithDisposable;var j=Rx.Scheduler.CurrentThread;g.Aggregate=function(l,m){return this.Scan0(l,m).Final();};g.Aggregate1=function(l){return this.Scan1(l).Final();};g.IsEmpty=function(){var l=this;return i(function(m){return l.Subscribe(function(){m.OnNext(false);m.OnCompleted();},function(n){m.OnError(n);},function(){m.OnNext(true);m.OnCompleted();});});};g.Any=function(l){if(l===c)return this.IsEmpty().Select(function(m){return !m;});return this.Where(l).Any();};g.All=function(l){if(l===c)l=e;return this.Where(function(m){return !l(m);}).IsEmpty();};g.Contains=function(l,m){if(m===c)m=d;return this.Where(function(n){return m(n,l);}).Any();};g.Count=function(){return this.Aggregate(0,function(l,m){return l+1;});};g.Sum=function(){return this.Aggregate(0,function(l,m){return l+m;});};g.Average=function(){return this.Scan({sum:0,count:0},function(l,m){return {sum:l.sum+m,count:l.count+1};}).Final().Select(function(l){return l.sum/l.count;});};g.Final=function(){var l=this;return i(function(m){var n;var o=false;return l.Subscribe(function(p){o=true;n=p;},function(p){m.OnError(p);},function(){if(!o)m.OnError(h);m.OnNext(n);m.OnCompleted();});});};var k=function(l,m,n){return i(function(o){var p=false;var q;var r;return l.Subscribe(function(s){var t;try{t=m(s);}catch(v){o.OnError(v);return;}if(!p){p=true;q=t;r=s;return;}var u;try{u=n(q,t);}catch(v){o.OnError(v);return;}if(u){q=t;r=s;}},function(s){o.OnError(s);},function(){if(!p)o.OnError(h);o.OnNext(r);o.OnCompleted();});});};g.Min=g.MinBy=function(l,m){if(l===c)l=e;if(m===c)m=function(n,o){return o<n;};return k(this,l,m);};g.Max=g.MaxBy=function(l,m){if(l===c)l=e;if(m===c)m=function(n,o){return o>n;};return k(this,l,m);};})();