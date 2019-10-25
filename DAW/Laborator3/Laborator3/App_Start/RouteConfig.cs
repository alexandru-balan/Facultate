using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Laborator3
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "ArticleIndex",
                url: "{controller}/{action}",
                defaults: new {controller = "Article", action = "Index"}
                );

            routes.MapRoute(
                name: "ArticleShow",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Article", action = "Show", id = UrlParameter.Optional }
                );
            routes.MapRoute(
                name: "ArticleShowDif",
                url: "article/show/{id}",
                defaults: new { controller = "Article", action = "ShowError", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "ArticleNewPost",
                url: "article/{action}/{id}/{title}/{content}",
                defaults: new { controller = "Article", action = "New", id = UrlParameter.Optional, title = UrlParameter.Optional, content = UrlParameter.Optional }
                );
            routes.MapRoute(
                name: "ArticleNew",
                url: "{controller}/{action}",
                defaults: new { controller = "Article", action = "New" }
                );

            routes.MapRoute(
                name: "ArticleEdit",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Article", action = "Edit", id = UrlParameter.Optional }
                );
            routes.MapRoute(
                name: "ArticleEditPut",
                url: "article/{action}",
                defaults: new { controller = "Article", action = "Edit" }
                );

            routes.MapRoute(
                name: "ArticleDelete",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Article", action = "Delete", id = UrlParameter.Optional }
                );
            routes.MapRoute(
                name: "ArticleDeleteDif",
                url: "article/{action}/{id}",
                defaults: new { controller = "Article", action = "DeleteConf", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "Default",
                url: "Article/Index",
                defaults: new { controller = "Article", action = "Index" }
            );
        }
    }
}
