(function($) {
    var app = $.sammy('#main', function() {
        this.use('Template');
        this.use('Session');

        this.around(function(callback) {
            var context = this;
            this.load('data/items.json')
                .then(function(items) {
                    context.items = items;
                })
                .then(callback);
        });
        this.get('#/', function(context) {
            context.app.swap('');
            $.each(context.items, function(i, item) {
                context.render('templates/item.template', {id: i, item: item})
                       .appendTo(context.$element());
            });
        });

        this.get('#/item/:id', function(context) {
            context.item = context.items[context.params['id']];
            if (!context.item) return context.notFound();
            context.partial('templates/item_detail.template');
        });

        this.post("#/cart", function(context) {
            var item_id = context.params['item_id'];

            var cart = context.session('cart', function() {
                return {};
            });
            if (!cart[item_id])
                cart[item_id] = 0;

            cart[item_id] += parseInt(context.params['quantity'], 10)
            context.session('cart', cart);
            this.trigger('update-cart');
        });

        this.bind('update-cart', function() {
            var sum = 0;
            $.each(this.session('cart') || {}, function(id, quantity) {
                sum += quantity;
            });

            $('.cart-info')
                .find('.cart-items').text(sum).end()
                .animate({paddingTop: '30px'})
                .animate({paddingTop: '10px'});
        });

        this.bind('run', function() {
            this.trigger('update-cart');
        })
    });


    $(function() {
        app.run('#/');
    });
})(jQuery);
